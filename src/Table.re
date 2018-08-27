type state = {
  session: Trainer.session,
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

let make = (~table: Trainer.table, _children) => {
  ...component,
  initialState: () => {
    session: List.hd(table.sessions),
    sessions: table.sessions,
  },
  reducer: (action, state: state) =>
    switch (action) {
    | Select(session) => Js.log(session); ReasonReact.Update({...state, session})
    | Finish => ReasonReact.NoUpdate
    },
  render: self =>
    <div>
      {
        listed(
          (session: Trainer.session) =>
            <button
              key={session.name}
              onClick={_ => self.send(Select(session))}>
              {text(session.name)}
            </button>,
          table.sessions,
        )
      }
      <Session session=self.state.session onComplete=Js.log/>
    </div>,
};