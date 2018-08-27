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
  | Next
  | Finish;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Session");

let shift = (session: exercisesList) => {
  session: List.tl(session),
  current: List.hd(session),
};

let extendSlice = (finished, {session, current}) :state=> {finished,session,current}

let update = (state: state) =>
  switch (state.session) {
  | [] => {...state, finished: true}
  | exercises => shift(exercises) |> extendSlice (false)
  };

let make = (~session: Trainer.session, ~onComplete, _children) => {
  ...component,
  initialState: () => shift(session.exercises) |> extendSlice (false) ,
  willReceiveProps: _self => shift(session.exercises) |> extendSlice (false), 
  reducer: (action, state: state) =>
    switch (action) {
    | Next => ReasonReact.Update(update(state))
    | Finish =>
      onComplete(session.name);
      ReasonReact.NoUpdate;
    },
  render: self =>
    !self.state.finished ?
      <RunExercise
        exercise={self.state.current}
        onComplete={_name => self.send(Next)}
      /> :
      <button onClick={_ => self.send(Finish)}>
        {ReasonReact.string("Finish session")}
      </button>,
};
