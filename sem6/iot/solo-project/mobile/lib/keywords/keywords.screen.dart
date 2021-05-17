import 'package:flutter/material.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/firestore.service/firestore.service.dart';
import 'package:mobile/keywords/keywords.card.dart';
import 'package:mobile/keywords/keywords.model.dart';

class KeywordsScreen extends StatefulWidget {
  final FirestoreService _firestoreService;

  KeywordsScreen({Key? key})
      : _firestoreService = GetIt.I.get<FirestoreService>(),
        super(key: key);

  @override
  State<StatefulWidget> createState() => _KeywordsScreenState();
}

class _KeywordsScreenState extends State<KeywordsScreen> {
  List<KeywordModel> keywords = [];
  bool valid = false;
  final TextEditingController _keywordController = TextEditingController();
  final wordRe = RegExp(r'^\w+$');

  @override
  initState() {
    widget._firestoreService.keywords.stream.listen((event) {
      setState(() => this.keywords = event);
    });
    super.initState();
  }

  _validate(String kw) {
    if (!wordRe.hasMatch(kw) || keywords.contains(kw)) {
      setState(() {
        valid = false;
      });
      return;
    }
    setState(() {
      valid = true;
    });
  }

  _submitKeyword() {
    String kw = _keywordController.text;
    widget._firestoreService.writeKeyword(kw);
  }

  @override
  Widget build(BuildContext context) => Scaffold(
        appBar: AppBar(title: Text('Keywords')),
        body: Padding(
            padding: EdgeInsets.all(5),
            child: Column(children: [
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children: [
                  Expanded(
                      flex: 3,
                      child: Container(
                        height: 60,
                        child: TextField(
                          controller: _keywordController,
                          onChanged: _validate,
                          decoration: InputDecoration(
                              border: OutlineInputBorder(),
                              hintText: 'Add new keyword'),
                        ),
                      )),
                  Flexible(
                      flex: 1,
                      child: Container(
                          height: 60,
                          child: ElevatedButton(
                            onPressed: () => _submitKeyword(),
                            child: Text('ADD'),
                          )))
                ],
              ),
              Expanded(
                  child: keywords.length != 0
                      ? ListView(
                          children:
                              this.keywords.map((e) => KeywordCard(e)).toList(),
                        )
                      : Center(
                          child: Text(
                          'No keywords created',
                          style: Theme.of(context).textTheme.headline1,
                        ))),
            ])),
      );
}
