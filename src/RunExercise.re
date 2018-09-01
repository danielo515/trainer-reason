/* State declaration */
type state = {
  count: int,
  reps: int,
  series: list(int),
  resting: bool,
  finished: bool,
};

/* Action declaration */
type action =
  | Complete
  | Finish
  | RestFinish;

let component = ReasonReact.reducerComponent("Exercise");

let initialState = ({series}: Trainer.exercise_run) => {
  count: 0,
  resting: false,
  finished: false,
  series: List.tl(series),
  reps: List.hd(series),
};

let make = (~exercise: Trainer.exercise_run, ~onComplete, _children) => {
  ...component,
  initialState: () => initialState(exercise),
  willReceiveProps: _self => initialState(exercise), /* Reset the count on exercise update */
  reducer: (action, state) =>
    switch (action) {
    | RestFinish =>
      let finished = List.length(state.series) == 0;
      ReasonReact.Update({
        resting: false,
        finished,
        count: state.count + 1,
        series:  finished ? state.series : List.tl(state.series),
        reps: finished ? state.reps : List.hd(state.series),
      });

    | Complete => ReasonReact.Update({...state, resting: true})
    | Finish =>
      onComplete(exercise.name);
      ReasonReact.Update({
        ...state,
        count: 0,
        resting: false,
        finished: false,
      });
    },
  render: self => {
    let message = "You are training: " ++ exercise.name;
    <div>
      <span> {ReasonReact.string(message)} </span>
      {
        !self.state.finished ?
          <Button
            disabled={self.state.resting}
            onClick={_event => self.send(Complete)}
            text={self.state.resting ? "Resting..." : "Done!"}
          /> :
          <Button
            disabled=false
            onClick={_e => self.send(Finish)}
            text="Next Exercise!"
          />
      }
      <br />
      {ReasonReact.string("Count " ++ string_of_int(self.state.count))}
      <br />
      {ReasonReact.string("Rest ")}
      <CountDown
        time={exercise.rest}
        running={self.state.resting}
        onFinish={_ => self.send(RestFinish)}
      />
      <br />
      {ReasonReact.string("REPS " ++ string_of_int(self.state.reps))}
      <HorizontalList items={exercise.series} index={self.state.count} />
      <br />
      {
        ReasonReact.string(
          "Remaining " ++ string_of_int(List.length(self.state.series)),
        )
      }
    </div>;
  },
};