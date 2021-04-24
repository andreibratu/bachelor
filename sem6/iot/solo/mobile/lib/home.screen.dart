import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/firestore.service/firestore.service.dart';
import 'package:mobile/log/log.card.dart';
import 'package:mobile/log/log.model.dart';

class HomeScreen extends StatefulWidget {
  final FirestoreService _firestoreService;
  final String title;

  HomeScreen({Key? key, required this.title})
      : _firestoreService = GetIt.I.get<FirestoreService>(),
        super(key: key);

  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  List<LogModel> logs = [];

  @override
  void initState() {
    widget._firestoreService.logs.stream
        .listen((event) => setState(() => logs = event));
    super.initState();
  }

  @override
  Widget build(BuildContext context) => Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Padding(
          padding: EdgeInsets.all(5),
          child: logs.length != 0
              ? ListView(
                  children: this.logs.map((e) => LogCard(log: e)).toList(),
                )
              : Container(
                  width: double.infinity,
                  height: double.infinity,
                  alignment: Alignment.center,
                  child: Text(
                    'No phrases containing known keywords',
                    style: Theme.of(context).textTheme.headline1,
                    textAlign: TextAlign.center,
                  ),
                )),
      floatingActionButton: FloatingActionButton(
        onPressed: () => Navigator.of(context).pushNamed('/keywords'),
        tooltip: 'Increment',
        child: Icon(Icons.add),
      ));
}
