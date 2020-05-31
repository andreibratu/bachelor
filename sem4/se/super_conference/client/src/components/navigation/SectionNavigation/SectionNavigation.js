import React, {useState} from 'react';
import {Navigation} from 'baseui/side-navigation';
import {useLocation} from "react-router-dom";

const SectionNavigation = (props) => {
    const {pathname} = useLocation();
    const [location, setLocation] = useState(pathname);

    const {locations} = props;

    return (
        <div className={"SectionNavigation"}>
            <Navigation
                items={locations}
                activeItemId={location}
                onChange={({item}) => setLocation(item.itemId)}
                overrides={{
                    Root: {
                        style: ({$theme}) => {
                            return {
                                height: '100%',
                                backgroundColor: $theme.colors.mono200
                            };
                        }
                    }
                }}
            />
        </div>
    );
};

export default SectionNavigation;
