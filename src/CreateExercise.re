type state = Trainer.exercise_run;

  type action =
    | UpdateName(string)
    | UpdateRest(string)
    | Submit;
  
  let component = ReasonReact.reducerComponent("Create-exercise");
  
  let initialState = ():state => { name: "", rest: 30, series: [], completed: 0};
  
  open ReasonReact;
  
  let make = (~onSubmit, _children): ReasonReact.component(Trainer.exercise_run, 'a, action) => {
    ...component,
    initialState: () => initialState(),
    reducer: (action, state) =>
      switch (action) {
      | UpdateName(name) => Update({...state, name})
      | UpdateRest(value) => Update({...state, rest: int_of_string(value) })
      | Submit => UpdateWithSideEffects( initialState(), (_ => onSubmit(state)))
      },
    render: ({state, send }) =>
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
        <Button text="+Exercise" onClick=(_=> send(Submit))/>
      </div>,
  };
  