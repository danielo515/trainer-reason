
let puto: Trainer.exercise_def = { name: "Press de banca", image: "./banca.png", category: Torso};

let entrena_puto: Trainer.exercise_run = {
  name: "Press de banca",
  reps: 10,
  series: 2,
  rest: 5,
  completed: 0,
};

let dale: Trainer.table = {
  name: "Prueba",
  sessions: [{name: "Día 2", exercises: [entrena_puto]}],
  completed: 0,
};

let onComplete = name => Js.log("Exercise  "++ name ++ "Completed!!!")

ReactDOMRe.renderToElementWithId(<RunExercise exercise=entrena_puto onComplete />, "index2");
