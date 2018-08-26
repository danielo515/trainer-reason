/* State declaration */
type state = {
  count: int,
  rest: int,
  resting: bool,
  finished: bool,
};

/* Action declaration */
type action =
  | Complete
  | Finish
  | Rest(int);

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

let rec countDown = (amount, fn) =>
  if (amount > 0) {
    Js.Global.setTimeout(
      () => {
        fn(amount - 1);
        countDown(amount - 1, fn);
      },
      1000,
    )
    |> ignore;
  };

let make = (~exercise: Trainer.exercise_run, ~onComplete, _children) => {
  ...component,
  initialState: () => {count: 0, rest: 0, resting: false, finished: false},
  willReceiveProps: self => {...self.state, count: 0}, /* Reset the count on exercise update */
  reducer: (action, state) =>
    switch (action) {
    | Rest(remaining) =>
      let resting = remaining != 0;
      let completed = state.count == exercise.series;
      let finished = !resting && completed;
      ReasonReact.Update({...state, rest: remaining, resting, finished});

    | Complete =>
      ReasonReact.Update({
        ...state,
        count: state.count + 1,
        rest: exercise.rest,
        resting: true,
      })
    | Finish =>
      onComplete(exercise.name);
      ReasonReact.Update({...state, count: 0, resting: false, finished: false});
    },
  render: self => {
    let message = "You are training: " ++ exercise.name;
    <div>
      {ReasonReact.string(message)}
      {
        !self.state.finished 
        ? <button
            disabled={self.state.resting}
            onClick={
              _event => {
                self.send(Complete);
                countDown(exercise.rest, amount => self.send(Rest(amount)));
              }
            }>
            {ReasonReact.string(self.state.resting ? "Resting..." : "Done!")}
          </button> 
        : <button onClick={_e => self.send(Finish)}>
            {ReasonReact.string("Next Exercise!")}
          </button>
      }<br></br>
      {ReasonReact.string("Count " ++ string_of_int(self.state.count))}<br></br>
      {ReasonReact.string("Rest " ++ string_of_int(self.state.rest))}<br></br>
      {ReasonReact.string("Remaining " ++ string_of_int(exercise.series - self.state.count ))}
    </div>;
  },
};