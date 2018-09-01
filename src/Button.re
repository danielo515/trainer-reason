/* This is the basic component. */
let component = ReasonReact.statelessComponent("Button");

let make = (~onClick,~disabled,~text, _children) => {
  ...component,
  render: _self =>
  <button className="button is-primary is-fullwidth"
    disabled=disabled
    onClick
    >
    (Util.text(text))
  </button>
};