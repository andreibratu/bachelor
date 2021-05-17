import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/firestore.service/firestore.service.dart';
import 'package:mobile/home.screen.dart';

import 'keywords/keywords.screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  GetIt.I.registerSingleton(FirestoreService());
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        theme: ThemeData(
            primarySwatch: Colors.blue,
            textTheme: TextTheme(
                headline1: TextStyle(fontSize: 24, fontWeight: FontWeight.w600),
                bodyText1:
                    TextStyle(fontSize: 16.0, fontWeight: FontWeight.normal))),
        routes: {
          '/': (ctx) => HomeScreen(title: 'Monitor'),
          '/keywords': (ctx) => KeywordsScreen()
        },
        initialRoute: '/');
  }
}
