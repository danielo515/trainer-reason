/* This is the basic component. */
let component = ReasonReact.statelessComponent("Hero");

let make = children => {
  ...component,
  render: _self =>
    <section className="hero">
      <div className="hero-body">
        <div className="container has-text-centered"> ...children </div>
      </div>
    </section>,
};