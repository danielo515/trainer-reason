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
};

type updater = state => state;

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
      table: Some(List.hd(tables)),
    };
  };
};

let state =
  ref({
    table: None,
    tables: [],
    editing: false,
    completed_sessions: [],
  });

let selectTable = (~tableName, state): state => {
  ...state,
  table:
    try (
      Some(
        List.find(
          ({name}: Trainer.table) => name == tableName,
          state.tables,
        ),
      )
    ) {
    | Not_found => None
    },
};

let update = (fn: updater) => state := fn(state^);

let saveState = state => {
  let json = state |> Encode.state |> Json.stringify;
  Dom.Storage.(localStorage |> setItem("store", json));
};

let loadState = () =>
  state :=
    Dom.Storage.(localStorage |> getItem("store"))
    |> (
      fun
      | Some(str) => str |> Json.parseOrRaise |> Decode.state
      | _ => state^
    );

let startSession = (table, session) => {
  let newSession = {table, session, start: Js.Date.now(), _end: 0.0};
  let finish = state => {
    ...state,
    completed_sessions: [
      {...newSession, _end: Js.Date.now()},
      ...state.completed_sessions,
    ],
  };

  () => {
    update(finish);
    saveState(state^);
  };
};

let render = fn => fn(state^);

loadState();