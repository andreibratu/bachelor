package server.security.config;

import io.jsonwebtoken.ExpiredJwtException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.web.authentication.WebAuthenticationDetailsSource;
import org.springframework.stereotype.Component;
import org.springframework.web.filter.OncePerRequestFilter;
import server.security.service.JwtUserDetailsService;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@Component
public class JwtRequestFilter extends OncePerRequestFilter
{
    private final JwtUserDetailsService jwtUserDetailsService;

    private final JwtTokenUtil jwtTokenUtil;

    @Autowired
    public JwtRequestFilter(JwtUserDetailsService jwtUserDetailsService, JwtTokenUtil jwtTokenUtil)
    {
        this.jwtUserDetailsService = jwtUserDetailsService;
        this.jwtTokenUtil = jwtTokenUtil;
    }

    @Override
    protected void doFilterInternal(HttpServletRequest httpServletRequest,
                                    HttpServletResponse httpServletResponse,
                                    FilterChain filterChain)
    {
        final String requestTokenHeader = httpServletRequest.getHeader("Authorization");
        String username = null;
        String jwtToken = null;

        // JWT Token is in the form "Bearer token". Remove Bearer word and get only the Token
        if (requestTokenHeader != null && requestTokenHeader.startsWith("Bearer "))
        {
            jwtToken = requestTokenHeader.substring(7);
            try {
                username = jwtTokenUtil.getUsernameFromToken(jwtToken);
            } catch (IllegalArgumentException e) {
                System.out.println("Unable to get JWT Token");
            } catch (ExpiredJwtException e) {
                System.out.println("JWT Token has expired");
            }
        }
        else
        {
            logger.warn("JWT Token does not begin with Bearer String");
        }
        // Once we get the token validate it.
        if (username != null && SecurityContextHolder.getContext().getAuthentication() == null)
        {
            UserDetails userDetails = this.jwtUserDetailsService.loadUserByUsername(username);
            // if token is valid configure Spring Security to manually set authentication
            if (jwtTokenUtil.validateToken(jwtToken, userDetails))
            {
                UsernamePasswordAuthenticationToken usernamePasswordAuthenticationToken =
                        new UsernamePasswordAuthenticationToken(
                            userDetails, null, userDetails.getAuthorities()
                );
                usernamePasswordAuthenticationToken
                        .setDetails(new WebAuthenticationDetailsSource().buildDetails(httpServletRequest));
                // After setting the Authentication in the context, we specify
                // that the current user is authenticated. So it passes the
                // Spring Security Configurations successfully.
                SecurityContextHolder.getContext().setAuthentication(usernamePasswordAuthenticationToken);
            }
        }
        try
        {
            filterChain.doFilter(httpServletRequest, httpServletResponse);
        }
        catch (IOException | ServletException e)
        {
            e.printStackTrace();
        }
    }
}
