/* State declaration */
type state = {
  count: int,
  rest: int,
  resting: bool,
};

/* Action declaration */
type action =
  | Complete
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
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {count: 0, rest: 0, resting: false},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Rest(remaining) =>
      let resting = remaining == 0 ? false : true;
      if (!resting && state.count == exercise.series) {
        onComplete(exercise.name);
      };
      ReasonReact.Update({...state, rest: remaining, resting});

    | Complete =>
      ReasonReact.Update({
        count: state.count + 1,
        rest: exercise.rest,
        resting: true,
      })
    },
  render: self => {
    let message = "You are training: " ++ exercise.name;
    <div>
      {ReasonReact.string(message)}
      <button
        disabled={self.state.resting}
        onClick={
          _event => {
            self.send(Complete);
            countDown(exercise.rest, amount => self.send(Rest(amount)));
          }
        }>
        {ReasonReact.string("Done!")}
      </button>
      {ReasonReact.string("Count " ++ string_of_int(self.state.count))}
      {ReasonReact.string("Rest " ++ string_of_int(self.state.rest))}
    </div>;
  },
};