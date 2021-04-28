function A = adaptiveQuadrature(f, a, b, err)
  I1 = simpson(f, a, b);
  I2 = simpson(f, a, (a + b) / 2) + simpson(f, (a + b) / 2, b);
  
  if (abs(I1 - I2) < 15 * err)
    A = I2;
  else
    A = adaptiveQuadrature(f, a, (a + b) / 2, err / 2) + adaptiveQuadrature(f, (a + b) / 2, b, err / 2);  
  end
end