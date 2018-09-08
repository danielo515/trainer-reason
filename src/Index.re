[%bs.raw {| require("./styles.scss") |}];
let stateDev = [%bs.raw {| require("./tabla") |}];

let listTables = (tables, onClick) =>
  tables
  |> Util.listToComponent((table: Trainer.table) =>
       <Button
         key={table.name}
         onClick={_ => onClick(table)}
         text={table.name}
       />
     );


Store.update( _=> Store.Decode.state (stateDev))

ReactDOMRe.renderToElementWithId(
  Store.render(state =>
    switch (state.table) {
    | None =>
      listTables(state.tables, table =>
        (
          Store.update(Store.selectTable(~tableName=table.name))
        )
      )
    | Some(table) => <Table table />
    }
  ),
  "index1",
);