import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:mobile/log/log.card.dart';

class HomeScreen extends StatefulWidget {
  HomeScreen({Key? key, this.title}) : super(key: key);

  final String? title;

  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  @override
  Widget build(BuildContext context) => Scaffold(
        appBar: AppBar(
          title: Text(widget.title!),
        ),
        body: Padding(
            padding: EdgeInsets.all(5),
            child: ListView(
              children: [LogCard(), LogCard(), LogCard()],
            )),
        // floatingActionButton: FloatingActionButton(
        //   onPressed: _incrementCounter,
        //   tooltip: 'Increment',
        //   child: Icon(Icons.add),
        // ),
      );
}
