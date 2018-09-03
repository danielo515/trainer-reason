// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Util$ReasonTrainer = require("./Util.bs.js");

function countDown(amount, fn) {
  if (amount > 0) {
    setTimeout((function () {
            Curry._1(fn, amount - 1 | 0);
            return countDown(amount - 1 | 0, fn);
          }), 10);
    return /* () */0;
  } else {
    return 0;
  }
}

var component = ReasonReact.reducerComponent("CountdownBar");

function initialState(time) {
  return /* record */[
          /* max */Caml_int32.imul(time, 100),
          /* current */0
        ];
}

function make(time, running, onFinish, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */(function (self) {
              if (running) {
                countDown(Caml_int32.imul(time, 100), (function (amount) {
                        return Curry._1(self[/* send */3], /* Tick */[amount]);
                      }));
              }
              return initialState(time);
            }),
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (param) {
              var state = param[/* state */1];
              return React.createElement("progress", {
                          className: "progress is-primary is-large",
                          max: String(state[/* max */0]),
                          value: String(state[/* current */1])
                        }, Util$ReasonTrainer.textInt(state[/* current */1]));
            }),
          /* initialState */(function () {
              return initialState(time);
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              var amount = action[0];
              if (amount === 0) {
                Curry._1(onFinish, /* () */0);
              }
              return /* Update */Block.__(0, [/* record */[
                          /* max */state[/* max */0],
                          /* current */amount
                        ]]);
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

var resolution = 100;

exports.countDown = countDown;
exports.component = component;
exports.resolution = resolution;
exports.initialState = initialState;
exports.make = make;
/* component Not a pure module */
