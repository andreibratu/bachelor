wallpapers = [
  'wallpaper_1.png',
  'wallpaper_2.jpg',
  'wallpaper_3.jpg',
  'wallpaper_4.jpg'
].map(fn => 'assets/' + fn)

function randint(low, high)
{
  // Generate a random value val s.t. low <= val < high
  var rand = Math.random()
  rand *= high
  rand = Math.floor(rand)
  return Math.max(low, rand)
}

function choice(iter)
{
  // Choose random element from iterable
  idx = randint(0, iter.length)
  return iter[idx]
}

function setRandomWallpaper()
{
  document.body.style.backgroundImage = `url(${choice(wallpapers)})`
}

function generateRandomLink()
{
  colors = ['pink', 'green', 'red', 'yellow', 'orange']

  polygon = document.createElement('polygon')
  pointsAttrVal = ''
  points = Array.apply(null, {length: randint(3, 7)})
                .map((_) => ({x: randint(0, 50), y: randint(0, 50)}))
  points.forEach(point => pointsAttrVal += `${point.x},${point.y} `)
  styleAttrVal = `fill:${choice(colors)};stroke:${choice(colors)};stroke-width:2`;
  styleAttrVal = styleAttrVal.trim()
  polygon.setAttribute('style', styleAttrVal)
  polygon.setAttribute('points', pointsAttrVal)

  svg = document.createElement('svg')
  svg.appendChild(polygon)

  return svg
}

function setLinkContainer()
{
  container = document.getElementById('link-container')
  container.innerHTML = ''
  for(i = 0; i < 10; i++)
  {
    container.appendChild(generateRandomLink())
  }
}

document.addEventListener("DOMContentLoaded", () => {
  setRandomWallpaper()
  setLinkContainer()
})
