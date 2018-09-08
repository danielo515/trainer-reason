[%bs.raw {| require("./styles.scss") |}];
/* let stateDev = [%bs.raw {| require("./tabla") |}]; */

let listTables = (tables, onClick) =>
  tables
  |> Util.listToComponent((table: Trainer.table) =>
       <Button
         key={table.name}
         onClick={_ => onClick(table)}
         text={table.name}
       />
     );

let render = (state: Store.state, send) =>
  switch (state.table) {
  | None =>
    listTables(state.tables, table =>  Store.SelectTable(table)  |> send )
  | Some(table) => <Table table send />
  };

ReactDOMRe.renderToElementWithId(<Store render />, "index1");