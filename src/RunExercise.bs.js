// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Button$ReactTemplate = require("./Button.bs.js");
var CountDown$ReactTemplate = require("./CountDown.bs.js");
var HorizontalList$ReactTemplate = require("./HorizontalList.bs.js");

var component = ReasonReact.reducerComponent("Exercise");

function initialState(param) {
  var series = param[/* series */1];
  return /* record */[
          /* count */0,
          /* reps */List.hd(series),
          /* series */List.tl(series),
          /* resting */false,
          /* finished */false
        ];
}

function make(exercise, onComplete, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */(function () {
              return initialState(exercise);
            }),
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var message = "You are training: " + exercise[/* name */0];
              var match = !self[/* state */1][/* finished */4];
              var tmp;
              if (match) {
                var match$1 = self[/* state */1][/* resting */3];
                tmp = ReasonReact.element(undefined, undefined, Button$ReactTemplate.make((function () {
                            return Curry._1(self[/* send */3], /* Complete */0);
                          }), self[/* state */1][/* resting */3], match$1 ? "Resting..." : "Done!", /* array */[]));
              } else {
                tmp = ReasonReact.element(undefined, undefined, Button$ReactTemplate.make((function () {
                            return Curry._1(self[/* send */3], /* Finish */1);
                          }), false, "Next Exercise!", /* array */[]));
              }
              return React.createElement("div", undefined, React.createElement("span", undefined, message), tmp, React.createElement("br", undefined), "Count " + String(self[/* state */1][/* count */0]), React.createElement("br", undefined), "Rest ", ReasonReact.element(undefined, undefined, CountDown$ReactTemplate.make(exercise[/* rest */2], self[/* state */1][/* resting */3], (function () {
                                    return Curry._1(self[/* send */3], /* RestFinish */2);
                                  }), /* array */[])), React.createElement("br", undefined), "REPS " + String(self[/* state */1][/* reps */1]), ReasonReact.element(undefined, undefined, HorizontalList$ReactTemplate.make(exercise[/* series */1], self[/* state */1][/* count */0], /* array */[])), React.createElement("br", undefined), "Remaining " + String(List.length(self[/* state */1][/* series */2])));
            }),
          /* initialState */(function () {
              return initialState(exercise);
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              switch (action) {
                case 0 : 
                    return /* Update */Block.__(0, [/* record */[
                                /* count */state[/* count */0] + 1 | 0,
                                /* reps */List.hd(state[/* series */2]),
                                /* series */List.tl(state[/* series */2]),
                                /* resting */true,
                                /* finished */state[/* finished */4]
                              ]]);
                case 1 : 
                    Curry._1(onComplete, exercise[/* name */0]);
                    return /* Update */Block.__(0, [/* record */[
                                /* count */0,
                                /* reps */state[/* reps */1],
                                /* series */state[/* series */2],
                                /* resting */false,
                                /* finished */false
                              ]]);
                case 2 : 
                    var completed = List.length(state[/* series */2]) === 0;
                    return /* Update */Block.__(0, [/* record */[
                                /* count */state[/* count */0],
                                /* reps */state[/* reps */1],
                                /* series */state[/* series */2],
                                /* resting */false,
                                /* finished */completed
                              ]]);
                
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.initialState = initialState;
exports.make = make;
/* component Not a pure module */
