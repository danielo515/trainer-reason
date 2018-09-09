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
    <div>
    (listTables(state.tables, table =>  Store.SelectTable(table)  |> send ))
    <Button text="+" onClick=(_=>send(Store.CreateTable))/>
    </div>
  | Some(table) => <Table table send />
  | Creating => <CreateTable send/>
  };

ReactDOMRe.renderToElementWithId(<Store render />, "index1");