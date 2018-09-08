// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Json = require("@glennsl/bs-json/src/Json.bs.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Json_encode = require("@glennsl/bs-json/src/Json_encode.bs.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Trainer$ReasonTrainer = require("./Trainer.bs.js");

function startSession(table, session) {
  var newSession_002 = /* start */Date.now();
  return (function (state) {
      return /* record */[
              /* table */state[/* table */0],
              /* tables */state[/* tables */1],
              /* editing */state[/* editing */2],
              /* completed_sessions : :: */[
                /* record */[
                  /* table */table,
                  /* session */session,
                  newSession_002,
                  /* _end */Date.now()
                ],
                state[/* completed_sessions */3]
              ],
              /* finishSession */state[/* finishSession */4]
            ];
    });
}

var component = ReasonReact.reducerComponent("Store");

function session(param) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "start",
                param[/* start */2]
              ],
              /* :: */[
                /* tuple */[
                  "end",
                  param[/* _end */3]
                ],
                /* :: */[
                  /* tuple */[
                    "table",
                    param[/* table */0]
                  ],
                  /* :: */[
                    /* tuple */[
                      "session",
                      param[/* session */1]
                    ],
                    /* [] */0
                  ]
                ]
              ]
            ]);
}

function state(param) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "tables",
                Json_encode.list(Trainer$ReasonTrainer.Encode[/* table */2], param[/* tables */1])
              ],
              /* :: */[
                /* tuple */[
                  "completed_sessions",
                  Json_encode.list(session, param[/* completed_sessions */3])
                ],
                /* [] */0
              ]
            ]);
}

var Encode = /* module */[
  /* session */session,
  /* state */state
];

function session$1(str) {
  return /* record */[
          /* table */Json_decode.field("table", Json_decode.string, str),
          /* session */Json_decode.field("session", Json_decode.string, str),
          /* start */Json_decode.field("start", Json_decode.$$float, str),
          /* _end */Json_decode.field("end", Json_decode.$$float, str)
        ];
}

function state$1(str) {
  var partial_arg = Trainer$ReasonTrainer.Decode[/* table */2];
  var tables = Json_decode.field("tables", (function (param) {
          return Json_decode.list(partial_arg, param);
        }), str);
  return /* record */[
          /* table */undefined,
          /* tables */tables,
          /* editing */false,
          /* completed_sessions */Json_decode.field("completed_sessions", (function (param) {
                  return Json_decode.list(session$1, param);
                }), str),
          /* finishSession */undefined
        ];
}

var Decode = /* module */[
  /* session */session$1,
  /* state */state$1
];

var initialState = /* record */[
  /* table */undefined,
  /* tables : [] */0,
  /* editing */false,
  /* completed_sessions : [] */0,
  /* finishSession */undefined
];

function loadState() {
  var param = localStorage.getItem("store");
  if (param !== null) {
    return state$1(Json.parseOrRaise(param));
  } else {
    return initialState;
  }
}

function saveState(state$2) {
  var json = Json.stringify(state(state$2));
  localStorage.setItem("store", json);
  return /* () */0;
}

function make(render, _) {
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
              return Curry._2(render, self[/* state */1], self[/* send */3]);
            }),
          /* initialState */loadState,
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (typeof action === "number") {
                if (action === 0) {
                  var match = state[/* finishSession */4];
                  if (match !== undefined) {
                    return /* UpdateWithSideEffects */Block.__(2, [
                              Curry._1(match, state),
                              (function (self) {
                                  return saveState(self[/* state */1]);
                                })
                            ]);
                  } else {
                    return /* NoUpdate */0;
                  }
                } else {
                  return /* Update */Block.__(0, [/* record */[
                              /* table */undefined,
                              /* tables */state[/* tables */1],
                              /* editing */state[/* editing */2],
                              /* completed_sessions */state[/* completed_sessions */3],
                              /* finishSession */state[/* finishSession */4]
                            ]]);
                }
              } else if (action.tag) {
                return /* Update */Block.__(0, [/* record */[
                            /* table */action[0],
                            /* tables */state[/* tables */1],
                            /* editing */state[/* editing */2],
                            /* completed_sessions */state[/* completed_sessions */3],
                            /* finishSession */state[/* finishSession */4]
                          ]]);
              } else {
                var match$1 = action[0];
                return /* Update */Block.__(0, [/* record */[
                            /* table */state[/* table */0],
                            /* tables */state[/* tables */1],
                            /* editing */state[/* editing */2],
                            /* completed_sessions */state[/* completed_sessions */3],
                            /* finishSession */startSession(match$1[0], match$1[1])
                          ]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.startSession = startSession;
exports.component = component;
exports.Encode = Encode;
exports.Decode = Decode;
exports.initialState = initialState;
exports.loadState = loadState;
exports.saveState = saveState;
exports.make = make;
/* component Not a pure module */
