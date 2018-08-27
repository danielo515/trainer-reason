let puto: Trainer.exercise_def = {
  name: "Press de banca",
  image: "./banca.png",
  category: Torso,
};

let entrena_puto: Trainer.exercise_run = {
  name: "Press de banca",
  reps: 10,
  series: 2,
  rest: 2,
  completed: 0,
};
let entrena_zorra: Trainer.exercise_run = {
  name: "Press de hombro",
  reps: 10,
  series: 2,
  rest: 2,
  completed: 0,
};

let dale: Trainer.table = {
  name: "Prueba",
  sessions: [
    {name: "Day 1", exercises: [entrena_zorra]},
    {name: "Day 2", exercises: [entrena_puto, entrena_zorra]},
  ],
  completed: 0,
};

let onComplete = name => Js.log("Session  " ++ name ++ "Completed!!!");

/* ReactDOMRe.renderToElementWithId(
     <Session session=List.hd(dale.sessions) onComplete />,
     "index2",
   ); */

ReactDOMRe.renderToElementWithId(<Table table=dale />, "index1");