/* This is the basic component. */
let component = ReasonReact.statelessComponent("HorizontalList");

let make = (~items: list(int), ~index: int, _children) => {
  ...component,
  render: _self =>
    <div className="tags">
      {
        List.mapi(
          (idx, item) =>
            <span key=string_of_int(idx) className={"tag is-large " ++ (idx == index ? "is-primary" : "is-light")}>
              {item |> string_of_int |> Util.text}
            </span>,
          items,
        )
        |> Util.componentFromList
      }
    </div>,
};