import 'package:cross/redux/app.reducer.dart';
import 'package:cross/redux/app.state.dart';
import 'package:cross/redux/entry.entity.dart';
import 'package:cross/views/main.screen.dart';
import 'package:flutter/material.dart';
import 'package:flutter_redux/flutter_redux.dart';
import 'package:redux/redux.dart';

void main() => runApp(MindfulApp());

class MindfulApp extends StatefulWidget {
  final store = Store<AppState>(appReducer,
      initialState: AppState(entries: [
        Entry(
            title: "Super mega cool",
            description: "Ce scrie mai sus",
            color: Colors.teal),
        Entry(
            title: "Today is a sad day",
            description:
                "UNLESS WE ARE TALKING ABOUT THESE GAINS SUPER MEGA COOl",
            color: Colors.lightGreen)
      ], currEntry: null));

  @override
  _MindfulAppState createState() => _MindfulAppState(store: store);
}

class _MindfulAppState extends State<MindfulApp> {
  final Store store;

  _MindfulAppState({@required this.store});

  @override
  Widget build(BuildContext context) {
    return StoreProvider(
        store: store,
        child: MaterialApp(
          title: 'Mindful',
          theme: ThemeData(
            primaryColor: Colors.white,
            visualDensity: VisualDensity.adaptivePlatformDensity,
          ),
          home: MainScreen(),
        ));
  }
}
