type session = {
  table: string,
  session: string,
  start: float,
  _end: float,
};

type state = {
  table: option(Trainer.table),
  tables: list(Trainer.table),
  editing: bool,
  completed_sessions: list(session),
  finishSession: option(state => state),
};

type updater = state => state;
type sessionName = string;
type tableName = string;
type sessionId = (tableName, sessionName);

type action =
  | StartSession(sessionId)
  | FinishSession
  | SelectTable(Trainer.table)
  | ClearTable;

let startSession = (table, session) => {
  let newSession = {table, session, start: Js.Date.now(), _end: 0.0};
  let finish = state => {
    ...state,
    completed_sessions: [
      {...newSession, _end: Js.Date.now()},
      ...state.completed_sessions,
    ],
  };

  finish;
};

let component = ReasonReact.reducerComponent("Store");

module Encode = {
  open Json_encode;

  let session = ({start, _end, table, session}) =>
    object_([
      ("start", float(start)),
      ("end", float(_end)),
      ("table", string(table)),
      ("session", string(session)),
    ]);

  let state = ({tables, completed_sessions}) =>
    object_([
      ("tables", list(Trainer.Encode.table, tables)),
      ("completed_sessions", list(session, completed_sessions)),
    ]);
};

module Decode = {
  open Json_decode;
  let session = str => {
    start: field("start", float, str),
    _end: field("end", float, str),
    table: field("table", string, str),
    session: field("session", string, str),
  };

  let state = str => {
    let tables = field("tables", list(Trainer.Decode.table), str);
    {
      tables,
      completed_sessions: field("completed_sessions", list(session), str),
      editing: false,
      finishSession: None,
      table: None,
    };
  };
};

let initialState = {
  tables: [],
  editing: false,
  completed_sessions: [],
  finishSession: None,
  table: None,
};

let loadState = () =>
  Dom.Storage.(localStorage |> getItem("store"))
  |> (
    fun
    | Some(str) => str |> Json.parseOrRaise |> Decode.state
    | _ => initialState
  );

let saveState = state => {
  let json = state |> Encode.state |> Json.stringify;
  Dom.Storage.(localStorage |> setItem("store", json));
};

let make = (~render, _children) => {
  ...component,
  initialState: loadState,
  reducer: (action, state) =>
    ReasonReact.(
      switch (action) {
      | ClearTable => Update({...state, table: None})
      | SelectTable(table) => Update({...state, table: Some(table)})
      | StartSession((tableName, sessionName)) =>
        Update({
          ...state,
          finishSession: Some(startSession(tableName, sessionName)),
        })
      | FinishSession =>
        switch (state.finishSession) {
        | Some(fn) => UpdateWithSideEffects(fn(state), self => saveState(self.state))
        | None => NoUpdate
        }
      }
    ),
  render: self => render(self.state, self.send),
};