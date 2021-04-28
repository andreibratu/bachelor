import 'package:flutter/material.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/firestore.service/firestore.service.dart';
import 'package:mobile/keywords/keywords.model.dart';

class KeywordCard extends StatelessWidget {
  final KeywordModel _keywordModel;
  final FirestoreService _firestoreService;

  KeywordCard(KeywordModel model)
      : _keywordModel = model,
        _firestoreService = GetIt.I.get<FirestoreService>();

  @override
  Widget build(BuildContext context) {
    TextStyle headingOne = Theme.of(context).textTheme.headline1!;

    return Container(
      height: 100,
      width: double.infinity,
      child: Card(
        color: Colors.white70,
        shadowColor: Colors.blueGrey,
        child: Padding(
          padding: EdgeInsets.all(5),
          child: Row(
            mainAxisAlignment: MainAxisAlignment.spaceBetween,
            children: [
              Expanded(
                  flex: 2,
                  child: Text(
                    'Keyword: ${_keywordModel.keyword}',
                    style: headingOne,
                  )),
              Flexible(
                  flex: 1,
                  child: Text(
                    'Count: ${_keywordModel.count.toString()}',
                    style: headingOne,
                  )),
              Flexible(
                  flex: 1,
                  child: IconButton(
                    icon: Icon(
                      Icons.delete,
                      size: 30,
                    ),
                    onPressed: () =>
                        _firestoreService.deleteKeyword(_keywordModel.id),
                  ))
            ],
          ),
        ),
      ),
    );
  }
}
