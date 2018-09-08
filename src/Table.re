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
       <button
         className="button is-primary is-fullwidth is-outlined"
         key={session.name}
         onClick={_ => onClick(session)}>
         {Util.text(session.name)}
       </button>
     );

let make = (~table: Trainer.table, ~send, _children) => {
  ...component,
  initialState: () => {
    session: NotSelected,
    sessions: table.sessions,
  },
  reducer: (action, state: state) =>
    switch (action) {
    | Select(session) =>
      ReasonReact.UpdateWithSideEffects({
        ...state,
        session: Selected(session),
      },
      _self => send(Store.StartSession((table.name, session.name)))
      )
    | Finish =>
      ReasonReact.UpdateWithSideEffects(
        {...state, session: NotSelected},
        (
          _self => send(Store.FinishSession)
        ),
      )
    },
  render: self =>
    <div className="column">
      {
        switch (self.state.session) {
        | Selected(session) =>
          <Session session onComplete=(_ => self.send(Finish)) />
        | NotSelected =>
          <div>
            <Hero>
              <p className="title is-2"> {table.name |> Util.text} </p>
            </Hero>
            {
              listSessions(table.sessions, session =>
                self.send(Select(session))
              )
            }
            <Button text="Back" onClick=(_=> send(Store.ClearTable))/>
          </div>
        }
      }
    </div>,
};