function getScrollDirection()
{
  // Return false if scrolling up, else true for scrolling down
  if (typeof getScrollDirection.lastScrollTop == 'undefined')
  {
    getScrollDirection.lastScrollTop = 0;
  }
  var currentScroll = $(window).scrollTop();
  const direction = getScrollDirection.lastScrollTop - currentScroll;
  getScrollDirection.lastScrollTop = currentScroll;
  return direction < 0 ? 'down' : 'up';
}

function getCurrentSlide()
{
  // Get current slide, using the offset of the slide start from top
  if (typeof getCurrentSlide.offsets == 'undefined')
  {
    getCurrentSlide.offsets = [];
    for(i=1;i<=4;i++)
    {
      getCurrentSlide.offsets.push($(`#slide-${i}`).offset().top)
    }
  }
  var currentScroll = $(window).scrollTop();
  var slide = null;
  for(i=1;i<4;i++)
  {
    if(getCurrentSlide.offsets[i-1] <= currentScroll &&
    currentScroll < getCurrentSlide.offsets[i])
    {
      slide = i;
      break;
    }
  }
  return slide != null ? slide : 4;
}

$(document).ready(() =>
{
  $(window).scroll(function handler()
  {
    $(window).off('scroll');
    slide = getCurrentSlide();
    scrolling = getScrollDirection();
    console.log(slide, scrolling)
    if (slide < 4 && scrolling === 'down')
    {
      console.log('scroll-down');
      $([document.documentElement, document.body]).animate(
        { scrollTop: $(`#slide-${slide+1}`).offset().top },
        1000
      );
    }
    if (slide >= 1 && scrolling === 'up')
    {
      console.log('scroll-up');
      $([document.documentElement, document.body]).animate(
        { scrollTop: $(`#slide-${slide}`).offset().top },
        1000
      );
    }
    setTimeout(() => { $(window).scroll(handler) }, 1200);
  })
});
