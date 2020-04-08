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
  shapes = ['rectangle', 'square']

  a = document.createElement('a')
  a.setAttribute('href', 'google.com')
  a.innerHTML = "Link!"

  div = document.createElement('div')
  div.className = `${choice(shapes)} link-wrapper`
  div.style.background = choice(colors)

  div.appendChild(a)

  return div
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
