type bodyPart =
  | Arm
  | Legs
  | Shoulders
  | Torso;

type series = list(int);

type exercise_def = {
  name: string,
  image: string,
  category: bodyPart,
};

type exercise_run = {
  name: string,
  series,
  rest: int,
  completed: int,
};

type session = {
  name: string,
  exercises: list(exercise_run),
};

type table = {
  sessions: list(session),
  name: string,
  completed: int,
};

module Encode = {
  open Json_encode;
  let exercise = ({name, series, rest, completed}: exercise_run) =>
    object_([
      ("name", string(name)),
      ("rest", int(rest)),
      ("series", list(int, series)),
      ("completed", int(completed)),
    ]);

  let session = ({name, exercises}) =>
    object_([
      ("name", string(name)),
      ("exercises", exercises |> list(exercise)),
    ]);

  let table = ({name, sessions, completed}) =>
    object_([
      ("name", string(name)),
      ("completed", int(completed)),
      ("sessions", sessions |> list(session)),
    ]);
};

module Decode = {
  open Json_decode;
  let exercise = str => {
    name: field("name", string, str),
    rest: field("rest", int, str),
    series: field("series", list(int), str),
    completed: field("completed", int, str),
  }

  let session = str => {
    name: field("name", string, str),
    exercises: field("exercises", list(exercise), str),
  }
  
  let table = str => {
    name: field("name", string, str),
    completed: field("completed", int, str),
    sessions: field("sessions", list(session), str),
  };

};

let isCompleted = exercise =>
  List.length(exercise.series) == exercise.completed;

let newTable = name: table => {name, sessions: [], completed: 0};

let newSession = name: session => {name, exercises: []};

let newExercise = (~name, ~series, ~rest=30, ()) => {
  name,
  series,
  rest,
  completed: 0,
};

let serieCompleted = (ex: exercise_run) => {
  ...ex,
  completed: ex.completed + 1,
};

let insertExercise = (session, ~exercise) => {
  ...session,
  exercises: [exercise, ...session.exercises],
};

let addToSession = (table: table, sessionName, exercise): table => {
  ...table,
  sessions:
    List.map(
      (session: session) =>
        session.name == sessionName ?
          insertExercise(session, ~exercise) : session,
      table.sessions,
    ),
};

let addSession = (table, session) => {
  ...table,
  sessions: [session, ...table.sessions],
};

/* let emptyTable =
     newTable("Rabo")
     ->addSession({name: "No Existe", exercises: []})
     ->addToSession(
         "No Existe",
         newExercise(~name="Press anal",  ~series=[10,8,8,6,6], ()),
       )
     ->addToSession(
         "No Existe",
         newExercise(~name="Press Brutal", ~series=[10,10,8,6,6], ()),
       )
     ->addToSession(
         "No Existe",
         (newExercise(~name="Press Follamigo", ~series=[10,10,8,8,6], ~rest=45, ()) |> serieCompleted),
       );

   let logDir = [%raw x => "console.dir(x, {depth:12})"];

   logDir(Encode.table(emptyTable));

   logDir(
     emptyTable.sessions
     |> List.map(s => s.exercises)
     |> List.map(isCompleted)->List.map,
   ); */