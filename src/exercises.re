let press_banca: Trainer.exercise_run = {
    name: "Press de banca",
    series: [10, 8, 8, 6, 6],
    rest: 3,
    completed: 0,
  };
  let press_hombro: Trainer.exercise_run = {
    name: "Press de hombro",
    series: [10, 10, 8, 8, 6],
    rest: 1,
    completed: 0,
  };
  
  let dale: Trainer.table = {
    name: "Prueba",
    sessions: [
      {name: "Day 1", exercises: [press_hombro]},
      {name: "Day 2", exercises: [press_banca, press_hombro]},
    ],
    completed: 0,
  };