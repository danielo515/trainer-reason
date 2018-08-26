
type exercisesList = list(Trainer.exercise_run)

type state = {
  session: exercisesList,
  current: Trainer.exercise_run,
};

/* Action declaration */
type action =
  | Next;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Session");

let shift = (session: exercisesList) => {
    session: List.tl(session),
    current: List.hd(session),
  }

let make = (~session: Trainer.session, _children) => {
  ...component,
  initialState: () => shift(session.exercises),
  reducer: (action, state: state) =>
    switch (action) {
    | Next => ReasonReact.Update(shift(state.session))
    },
  render: self => <RunExercise exercise=self.state.current onComplete=(_name => self.send(Next)) />,
};