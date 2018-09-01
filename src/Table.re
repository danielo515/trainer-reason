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

let listSessions = (sessions, onClick) =>
  sessions
  |> Util.listToComponent((session: Trainer.session) =>
       <button className="button is-primary is-fullwidth is-outlined" key={session.name} onClick={_ => onClick(session)}>
         {Util.text(session.name)}
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