type state = Trainer.exercise_run;

type action =
  | UpdateName(string)
  | UpdateRest(string)
  | UpdateSerie((int, int))
  | AddSerie
  | Submit;

let component = ReasonReact.reducerComponent("Create-exercise");

let initialState = (): state => {
  name: "",
  rest: 30,
  series: [],
  completed: 0,
};

let setSerieAt = (x, i) => List.mapi((idx, y) => idx == i ? x : y);
open ReasonReact;

let make =
    (~onSubmit, _children)
    : ReasonReact.component(Trainer.exercise_run, 'a, action) => {
  ...component,
  initialState: () => initialState(),
  reducer: (action, state) =>
    switch (action) {
    | UpdateName(name) => Update({...state, name})
    | AddSerie => Update({...state, series: [10, ...state.series]})
    | UpdateRest(value) => Update({...state, rest: int_of_string(value)})
    | UpdateSerie((value, pos)) =>
      Update({...state, series: setSerieAt(value, pos, state.series)})
    | Submit => UpdateWithSideEffects(initialState(), (_ => onSubmit(state)))
    },
  render: ({state, send}) =>
    <div>
      <Input
        value={state.name}
        type_=Input.Text
        placeholder="Exercise name"
        onChange={value => send(UpdateName(value))}
      />
      <Input
        value={string_of_int(state.rest)}
        type_=Input.Number
        placeholder="Resting"
        onChange={value => send(UpdateRest(value))}
      />
      <Button text="+" onClick={_ => send(AddSerie)} />
      {
        List.mapi(
          (i, serie) =>
            <Input
              value=string_of_int(serie)
              type_=Input.Number
              key=string_of_int(i)
              onChange={value => send(UpdateSerie((int_of_string (value), i)))}
            />,
          state.series,
        )
        |> Array.of_list
        |> ReasonReact.array
      }
      <Button text="Save exercise" onClick={_ => send(Submit)} />
    </div>,
};