
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
    sessions: [{name: "Día 2", exercises: [entrena_puto,entrena_zorra]}],
    completed: 0,
  };

let onComplete = name => Js.log("Exercise  " ++ name ++ "Completed!!!");


ReactDOMRe.renderToElementWithId(
  <Session session=List.hd(dale.sessions) />,
  "index2",
);