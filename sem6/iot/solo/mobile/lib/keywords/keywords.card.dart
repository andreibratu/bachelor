import 'package:flutter/material.dart';
import 'package:mobile/keywords/keywords.model.dart';

class KeywordCard extends StatelessWidget {
  final KeywordModel _keywordModel;

  KeywordCard(KeywordModel model) : _keywordModel = model;

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
                    onPressed: () {},
                  ))
            ],
          ),
        ),
      ),
    );
  }
}
