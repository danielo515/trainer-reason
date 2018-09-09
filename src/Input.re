let component = ReasonReact.statelessComponent("Input");

let handleChange = (fn, evt) => fn(ReactEvent.Form.target(evt)##value);

type type_ = 
  | Text
  | Number;

let make = (~onChange, ~type_=Text, ~value, ~placeholder="", _children) => {
  let handler = handleChange(onChange);
  {
    ...component,
    render: _ =>
    switch type_ {
    | Number => <input className="input" placeholder value type_="number" onChange=handler />
    | Text => <input className="input" placeholder value type_="text" onChange=handler />
    }
      
  };
};