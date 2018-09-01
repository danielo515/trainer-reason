let rec countDown = (amount, fn) =>
  if (amount > 0) {
    Js.Global.setTimeout(
      () => {
        fn(amount - 1);
        countDown(amount - 1, fn);
      },
      10,
    )
    |> ignore;
  };

type state = {
  max: int,
  current: int,
};
type action =
  | Tick(int);


let component = ReasonReact.reducerComponent("Example");

let resolution = 100;
let initialState = time => {max: time * resolution, current: 0};

let make = (~time,~running, ~onFinish, _children) => {
  ...component,
  initialState: () => initialState(time),
  willReceiveProps: self => {
    if (running) countDown(time * resolution, amount => self.send(Tick(amount)));
    initialState(time); /* Reset on update */
  },
  reducer: (action, state) =>
    switch (action) {
    | Tick(amount) => {
      if(amount == 0) onFinish();
      ReasonReact.Update({...state, current: amount});
    }
    },
  render: ({state}) =>
    <progress
      className="progress is-primary is-large"
      value={string_of_int(state.current)}
      max={string_of_int(state.max)}>
      {Util.textInt(state.current)}
    </progress>,
};