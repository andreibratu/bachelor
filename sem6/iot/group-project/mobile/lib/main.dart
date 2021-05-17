import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/firestorage.service/firestorage.service.dart';
import 'package:mobile/form/form.screen.dart';

import 'firestore.service/firestore.service.dart';
import 'main.screen.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp();
  GetIt.I.registerSingleton(FirestoreService());
  GetIt.I.registerSingleton(FirestorageService());
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      routes: {'/main': (ctx) => MainScreen(), '/form': (ctx) => FormScreen()},
      initialRoute: '/main',
    );
  }
}
