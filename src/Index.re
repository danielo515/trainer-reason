
let puto: Trainer.exercise_def = { name: "Press de banca", image: "./banca.png", category: Torso};

let entrena_puto: Trainer.exercise_run = {
  name: "Press de banca",
  reps: 10,
  series: 5,
  rest: 30,
  completed: 0,
};

let dale: Trainer.table = {
  name: "Prueba",
  sessions: [{name: "Día 2", exercises: [entrena_puto]}],
  completed: 0,
};


ReactDOMRe.renderToElementWithId(<RunExercise exercise=entrena_puto />, "index2");
