type curSession =
  | NotSelected
  | Selected(Trainer.session);

type state = {
  session: curSession,
  sessions: list(Trainer.session),
  onFinish: option(unit => unit),
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

let make = (~table: Trainer.table, _children) => {
  ...component,
  initialState: () => {
    session: NotSelected,
    sessions: table.sessions,
    onFinish: None,
  },
  reducer: (action, state: state) =>
    switch (action) {
    | Select(session) =>
      ReasonReact.Update({
        ...state,
        session: Selected(session),
        onFinish: Some(Store.startSession(table.name, session.name)),
      })
    | Finish =>
      ReasonReact.UpdateWithSideEffects(
        {...state, session: NotSelected},
        (
          _self =>
            switch (state.onFinish) {
            | Some(fn) => fn()
            | None => ()
            }
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
          </div>
        }
      }
    </div>,
};