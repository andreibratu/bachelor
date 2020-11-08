import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

class RoundedButton extends StatelessWidget {
  final double borderRadius;
  final double width;
  final double height;
  final Color color;
  final Color disabledColor;
  final Function onPressed;
  final Widget child;

  RoundedButton(
      {@required this.borderRadius,
      @required this.width,
      @required this.height,
      @required this.onPressed,
      @required this.child,
      @required this.color,
      @required this.disabledColor});

  @override
  Widget build(BuildContext context) {
    var isDisabled = this.onPressed == null;
    var color = isDisabled ? this.disabledColor : this.color;

    return ButtonTheme(
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(this.borderRadius),
            side: BorderSide(color: color)),
        minWidth: this.width,
        height: this.height,
        child: RaisedButton(
          disabledColor: color,
          onPressed: this.onPressed,
          child: this.child,
          color: color,
        ));
  }
}
