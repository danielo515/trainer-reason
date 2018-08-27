// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Session$ReactTemplate = require("./Session.bs.js");

var component = ReasonReact.reducerComponent("Session");

function listed(fn, list) {
  return $$Array.of_list(List.map(fn, list));
}

function text(str) {
  return str;
}

function make(table, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              return React.createElement("div", undefined, $$Array.of_list(List.map((function (session) {
                                    return React.createElement("button", {
                                                key: session[/* name */0],
                                                onClick: (function () {
                                                    return Curry._1(self[/* send */3], /* Select */[session]);
                                                  })
                                              }, session[/* name */0]);
                                  }), table[/* sessions */0])), ReasonReact.element(undefined, undefined, Session$ReactTemplate.make(self[/* state */1][/* session */0], (function (prim) {
                                    console.log(prim);
                                    return /* () */0;
                                  }), /* array */[])));
            }),
          /* initialState */(function () {
              return /* record */[
                      /* session */List.hd(table[/* sessions */0]),
                      /* sessions */table[/* sessions */0]
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (action) {
                var session = action[0];
                console.log(session);
                return /* Update */Block.__(0, [/* record */[
                            /* session */session,
                            /* sessions */state[/* sessions */1]
                          ]]);
              } else {
                return /* NoUpdate */0;
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.listed = listed;
exports.text = text;
exports.make = make;
/* component Not a pure module */
