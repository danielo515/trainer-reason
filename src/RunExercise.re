module Image = {
  let component = ReasonReact.statelessComponent("Exercise-image");

  let make = (~className, ~src, _children) => {
    ...component,
    render: _self =>
      <figure className> <p className="image is-128x128 is-4by5"> <img src /> </p> </figure>,
  };
};

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
        series: finished ? state.series : List.tl(state.series),
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
    /* let message = "You are training: " ++ exercise.name; */
    let count = "Count " ++ string_of_int(self.state.count);
    <div>
      <article className="media">
        <Image
          className="media-left"
          src="https://bulma.io/images/placeholders/320x480.png"
        />
        <div className="media-content">
          <div className="content">
            <p className="title is-3"> {exercise.name |> Util.text} </p>
            <p className="subtitle is-4"> {count |> Util.text} </p>
            <p className="subtitle is-4"> {("Reps " ++ string_of_int(self.state.reps)) |> Util.text} </p>
          </div>
        </div>
      </article>
      {ReasonReact.string("Rest ")}
      <CountDown
        time={exercise.rest}
        running={self.state.resting}
        onFinish={_ => self.send(RestFinish)}
      />
      <HorizontalList items={exercise.series} index={self.state.count} />
      {
        !self.state.finished ?
          <Button
            disabled={self.state.resting}
            onClick={_event => self.send(Complete)}
            text={self.state.resting ? "Resting..." : "Done!"}
            big=true
          /> :
          <Button onClick={_e => self.send(Finish)} text="Next Exercise!" big=true />
      }
    </div>;
  },
};