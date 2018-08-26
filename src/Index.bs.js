// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Session$ReactTemplate = require("./Session.bs.js");

var entrena_puto = /* record */[
  /* name */"Press de banca",
  /* reps */10,
  /* series */2,
  /* rest */2,
  /* completed */0
];

var entrena_zorra = /* record */[
  /* name */"Press de hombro",
  /* reps */10,
  /* series */2,
  /* rest */2,
  /* completed */0
];

var dale_000 = /* sessions : :: */[
  /* record */[
    /* name */"D\xc3\xada 2",
    /* exercises : :: */[
      entrena_puto,
      /* :: */[
        entrena_zorra,
        /* [] */0
      ]
    ]
  ],
  /* [] */0
];

var dale = /* record */[
  dale_000,
  /* name */"Prueba",
  /* completed */0
];

function onComplete(name) {
  console.log("Exercise  " + (name + "Completed!!!"));
  return /* () */0;
}

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, Session$ReactTemplate.make(List.hd(dale_000), /* array */[])), "index2");

var puto = /* record */[
  /* name */"Press de banca",
  /* image */"./banca.png",
  /* category : Torso */3
];

exports.puto = puto;
exports.entrena_puto = entrena_puto;
exports.entrena_zorra = entrena_zorra;
exports.dale = dale;
exports.onComplete = onComplete;
/*  Not a pure module */
