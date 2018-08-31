type curSession =
  | NotSelected
  | Selected(Trainer.session);

type state = {
  session: curSession,
  sessions: list(Trainer.session),
};

/* Action declaration */
type action =
  | Select(Trainer.session)
  | Finish;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Session");

let listed = (fn, list) =>
  ReasonReact.array(Array.of_list(List.map(fn, list)));
let text = str => ReasonReact.string(str);

let listSessions = (sessions, onClick) =>
  sessions
  |> listed((session: Trainer.session) =>
       <button key={session.name} onClick={_ => onClick(session)}>
         {text(session.name)}
       </button>
     );

let make = (~table: Trainer.table, _children) => {
  ...component,
  initialState: () => {session: NotSelected, sessions: table.sessions},
  reducer: (action, state: state) =>
    switch (action) {
    | Select(session) =>
      Js.log(session);
      ReasonReact.Update({...state, session: Selected(session)});
    | Finish => ReasonReact.Update({...state, session: NotSelected})
    },
  render: self =>
    <div>
      {
        switch (self.state.session) {
        | Selected(session) =>
          <Session session onComplete=(_ => self.send(Finish)) />
        | NotSelected =>
          listSessions(table.sessions, session => self.send(Select(session)))
        }
      }
    </div>,
};