// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Util$ReasonTrainer = require("./Util.bs.js");
var Store$ReasonTrainer = require("./Store.bs.js");
var Table$ReasonTrainer = require("./Table.bs.js");
var Button$ReasonTrainer = require("./Button.bs.js");
var CreateTable$ReasonTrainer = require("./CreateTable.bs.js");

(( require("./styles.scss") ));

function listTables(tables, onClick) {
  return Util$ReasonTrainer.listToComponent((function (table) {
                return ReasonReact.element(table[/* name */1], undefined, Button$ReasonTrainer.make((function () {
                                  return Curry._1(onClick, table);
                                }), undefined, table[/* name */1], undefined, /* array */[]));
              }), tables);
}

function render(state, send) {
  var match = state[/* table */0];
  if (typeof match === "number") {
    if (match !== 0) {
      return ReasonReact.element(undefined, undefined, CreateTable$ReasonTrainer.make(send, /* array */[]));
    } else {
      return React.createElement("div", undefined, listTables(state[/* tables */1], (function (table) {
                        return Curry._1(send, /* SelectTable */Block.__(1, [table]));
                      })), ReasonReact.element(undefined, undefined, Button$ReasonTrainer.make((function () {
                            return Curry._1(send, /* CreateTable */2);
                          }), undefined, "+", undefined, /* array */[])));
    }
  } else {
    return ReasonReact.element(undefined, undefined, Table$ReasonTrainer.make(match[0], send, /* array */[]));
  }
}

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, Store$ReasonTrainer.make(render, /* array */[])), "index1");

exports.listTables = listTables;
exports.render = render;
/*  Not a pure module */
