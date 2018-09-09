type state = Trainer.table;

type action =
  | UpdateName(string)
  | AddSession(Trainer.session)
  | Submit;

let component = ReasonReact.reducerComponent("Create-table");

let initialState = ():state => {
  name: "",
  sessions: [],
  completed: 0
};

open ReasonReact;

let make = (~send: Store.action => unit, _children): ReasonReact.component(Trainer.table, 'a, action) => {
  ...component,
  initialState: () => initialState(),
  reducer: (action, state) =>
    switch (action) {
    | UpdateName(name) => Update({...state, name})
    | AddSession(session) =>
      Update({...state, sessions: [session, ...state.sessions]})
    | Submit => SideEffects((_ => send(Store.AddTable(state))))
    },
  render: ({state, send: ssend}) =>
    <div>
      <Input
        value={state.name}
        type_=Input.Text
        placeholder="Table name"
        onChange={value => ssend(UpdateName(value))}
      />
      <CreateSession onSubmit=(session => ssend(AddSession(session)))/>
      ( state |>  Trainer.Encode.table |> Json.stringify |> Util.text )
      <Button text="Save table" onClick=(_=> ssend(Submit))/>
    </div>,
};