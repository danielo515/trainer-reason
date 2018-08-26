type exercisesList = list(Trainer.exercise_run);

type state = {
  session: exercisesList,
  current: Trainer.exercise_run,
  finished: bool,
};

type nextSlice = {
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
};

let update = (state: state) =>
  switch (state.session) {
  | [] => {...state, finished: true}
  | _ =>
    let {session, current} = shift(state.session);
    {session, current, finished: false};
  };

let make = (~session: Trainer.session, _children) => {
  ...component,
  initialState: () => {
    let {session, current} = shift(session.exercises);
    {current, session, finished: false};
  },
  reducer: (action, state: state) =>
    switch (action) {
    | Next => ReasonReact.Update(update(state))
    },
  render: self =>
    !self.state.finished ?
      <RunExercise
        exercise={self.state.current}
        onComplete={_name => self.send(Next)}
      /> :
      <button> {ReasonReact.string("Finish session")} </button>,
};