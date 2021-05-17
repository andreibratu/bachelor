import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:mobile/generic/attribute.text.dart';

import 'attempt.model.dart';

class AttemptCard extends StatelessWidget {
  final AttemptModel attemptModel;
  final String finalPhotoUrl;
  final String username;

  const AttemptCard(
      {Key key, this.attemptModel, this.finalPhotoUrl, this.username})
      : super(key: key);

  @override
  Widget build(BuildContext context) => Container(
        height: 300,
        width: double.infinity,
        alignment: Alignment.bottomCenter,
        decoration: BoxDecoration(
            image: DecorationImage(
                image: NetworkImage(finalPhotoUrl), fit: BoxFit.fill)),
        child: Container(
          color: Colors.blue.withOpacity(0.8),
          height: 60,
          width: double.infinity,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Padding(
                  padding: EdgeInsets.all(5),
                  child: AttributeText(
                    attributeName: 'Name',
                    attributeValue: username,
                    textColor: Colors.white,
                  )),
              Padding(
                  padding: EdgeInsets.all(5),
                  child: AttributeText(
                    textColor: Colors.white,
                    attributeName: 'Attempt At',
                    attributeValue:
                        '${DateFormat('yyyy-MM-dd – kk:mm').format(attemptModel.createdAt)}',
                  ))
            ],
          ),
        ),
      );
}
