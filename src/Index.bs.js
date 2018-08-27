// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Table$ReactTemplate = require("./Table.bs.js");

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
    /* name */"Day 1",
    /* exercises : :: */[
      entrena_zorra,
      /* [] */0
    ]
  ],
  /* :: */[
    /* record */[
      /* name */"Day 2",
      /* exercises : :: */[
        entrena_puto,
        /* :: */[
          entrena_zorra,
          /* [] */0
        ]
      ]
    ],
    /* [] */0
  ]
];

var dale = /* record */[
  dale_000,
  /* name */"Prueba",
  /* completed */0
];

function onComplete(name) {
  console.log("Session  " + (name + "Completed!!!"));
  return /* () */0;
}

ReactDOMRe.renderToElementWithId(ReasonReact.element(undefined, undefined, Table$ReactTemplate.make(dale, /* array */[])), "index1");

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
