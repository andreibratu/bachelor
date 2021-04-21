import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:mobile/home.screen.dart';
import 'package:mobile/loading.screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  final Future<FirebaseApp> _initialization = Firebase.initializeApp();

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        theme: ThemeData(
            primarySwatch: Colors.blue,
            textTheme: TextTheme(
                bodyText1:
                    TextStyle(fontSize: 16.0, fontWeight: FontWeight.normal))),
        home: FutureBuilder(
            future: _initialization,
            builder: (context, snapshot) {
              if (snapshot.hasError) throw (snapshot.error.toString());

              if (snapshot.connectionState == ConnectionState.done)
                return HomeScreen(title: 'Super Firebase powers!');

              // Stil loading
              return LoadingScreen();
            }));
  }
}
