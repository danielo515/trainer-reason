/* This is the basic component. */
let component = ReasonReact.statelessComponent("Button");

let make = (~onClick,~disabled=false,~text,~big=true, _children) => {
  ...component,
  render: _self =>
  <button className=("button is-primary is-fullwidth " ++ (big ? "is-large" : ""))
    disabled=disabled
    onClick
    >
    (Util.text(text))
  </button>
};