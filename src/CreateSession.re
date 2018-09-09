type state = Trainer.session;

type action =
  | UpdateName(string)
  | AddExercise(Trainer.exercise_run)
  | Submit;

let component = ReasonReact.reducerComponent("Create-session");

let initialState = (): state => {name: "", exercises: []};

let listExercises = ex => Json.Encode.(list(Trainer.Encode.exercise))(ex) |> Json.stringify |> Util.text

open ReasonReact;

let make = (~onSubmit, _children): ReasonReact.component(state,'a,action) => {
  ...component,
  initialState: () => initialState(),
  reducer: (action, state) =>
    switch (action) {
    | UpdateName(name) => Update({...state, name})
    | AddExercise(ex) =>
      Update({...state, exercises: [ex, ...state.exercises]})
    | Submit => UpdateWithSideEffects(initialState(), (_ => onSubmit(state)))
    },
  render: ({state, send: ssend}) =>
    <div>
      <Input
        value={state.name}
        type_=Input.Text
        placeholder="Session Name"
        onChange={value => ssend(UpdateName(value))}
      />
      <CreateExercise onSubmit={exercise => ssend(AddExercise(exercise))} />
      <Button text="Save session" onClick=(_=> ssend(Submit))/>
      (listExercises(state.exercises))
    </div>,
};