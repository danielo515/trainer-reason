let componentFromList = list =>
list
|> Array.of_list
|>  ReasonReact.array;

let text = str => ReasonReact.string(str);

let listToComponent = (fn, list) =>
  ReasonReact.array(Array.of_list(List.map(fn, list)));