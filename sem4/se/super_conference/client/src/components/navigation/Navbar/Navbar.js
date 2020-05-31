import * as React from 'react';
import {
    ALIGN,
    HeaderNavigation,
    StyledNavigationItem as NavigationItem,
    StyledNavigationList as NavigationList,
} from 'baseui/header-navigation';
import {StyledLink as Link} from 'baseui/link';
import './Navbar.css'

export default () => (
    <HeaderNavigation>
        <NavigationList $align={ALIGN.left}>
            <NavigationItem>
                <Link href={'/dashboard'}><h1>CMS</h1></Link>
            </NavigationItem>
        </NavigationList>
        <NavigationList $align={ALIGN.center}/>
        <NavigationList $align={ALIGN.right}>
            <NavigationItem>
                <Link href={'/dashboard/conferences/my-conferences'}>Conferences</Link>
            </NavigationItem>
            <NavigationItem>
                <Link href={'/dashboard/proposals/my-proposals'}>Proposals</Link>
            </NavigationItem>
            <NavigationItem style={{marginRight: "2em"}}>
                <Link href={'/logout'}>Sign Out</Link>
            </NavigationItem>
        </NavigationList>
    </HeaderNavigation>
);
