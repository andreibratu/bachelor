import 'package:flutter/material.dart';
import 'package:mobile/generic/loading/loading.animation.dart';

class LoadingOverlay {
  final Widget _instance = Container(
    width: double.infinity,
    height: double.infinity,
    color: Color.fromRGBO(0, 0, 0, 0.6),
    alignment: Alignment.center,
    child: LoadingAnimation(),
  );

  OverlayEntry _displayScreen;

  LoadingOverlay.show(BuildContext context) {
    this._displayScreen = OverlayEntry(builder: (context) => this._instance);
    Overlay.of(context).insert(_displayScreen);
  }

  void dispose() {
    this._displayScreen.remove();
  }
}
